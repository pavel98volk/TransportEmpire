var map;
var info_window;
var places_service;
var direction_service;
var selected_road;

var mouseover				 = false;
var live_road				 = true;
var last_town_destination	 = true;
var nearest_town_added		 = true;

var marked_places	 = {};
var markers			 = {};

var roads			 = [];
var roads_display	 = [];
var ordered_markers	 = [];
var colors = ['#4682B4','#00FF00','#FF0000','#FFFF00','#FF1493','#8B008B','#000000','#FF4500','#8B4513','#FF00FF'];

function initMap() {
	var position = {lat: 50.4501, lng: 30.523400000000038}; //Kiyv
	map = new google.maps.Map(document.getElementById('map'), {
		center: position,
		zoom: 8
	});
	map.addListener('click', function(event){
		searchNearestTowns(event.latLng);
	});
	//var socket = new WebSocket("ws://10.1.3.121:1234");
	places_service = new google.maps.places.PlacesService(map);
	direction_service = new google.maps.DirectionsService;
}

function searchNearestTowns(click_position){
	//var filters = document.getElementById('filters');
	if (nearest_town_added == true){
		places_service.search({
			location: click_position,
			rankBy: google.maps.places.RankBy.DISTANCE,
			types: ['locality']
		}, searchCallback);
	} else {
		places_service.radarSearch({
			location: click_position,
			radius: 10000,
			types: ['locality']
		}, radarCallback);
	}
}

function searchCallback(results, status){
	if (status === google.maps.places.PlacesServiceStatus.OK){
		clearMarkers();
		createMarker(results[0]);
	}
}

function radarCallback(results, status){
	if (status === google.maps.places.PlacesServiceStatus.OK){
		clearMarkers();
		results.forEach(function(item){
			createMarker(item);
		});
	}
}

function clearMarkers(){
	for (place_id in markers){
		if (marked_places[place_id] === undefined){
			markers[place_id].setMap(null);
			delete markers[place_id];
		}
	}
}

function clearAllMarkers(){
	for (place_id in markers){
		markers[place_id].setMap(null);
		delete markers[place_id];
		if (marked_places[place_id] !== undefined){
			delete marked_places[place_id];
		}
	}
}

function createMarker(place){
	if (markers[place.place_id] !== undefined){
		return;
	}
	markers[place.place_id] = new google.maps.Marker({
		position: place.geometry.location,
		map: map,
		zIndex: 1
	});	
	if (nearest_town_added){
		addMarkerToRoad(place.place_id);
	}
	markers[place.place_id].addListener('click', function(){
		addMarkerToRoad(place.place_id);
	});
	markers[place.place_id].addListener('mouseover', function(){
		showInfoWindow(place.place_id);	
	});
	markers[place.place_id].addListener('mouseout', function(){
		hideInfoWindow(place.place_id);	
	});
}

function showInfoWindow(place_id){
	mouseover = true;
	setTimeout(function(){
			if (mouseover){
				places_service.getDetails({placeId: place_id}, infoCallback);
			}
		}, 600
	);
	markers[place_id].setZIndex(2);
}

function hideInfoWindow(place_id){
	mouseover = false;
	if (markers[place_id] !== undefined){
		markers[place_id].setZIndex(1);
		if (info_window !==undefined){
			info_window.close();
			delete info_window;
		}
	}
}

function addMarkerToRoad(place_id) {
	places_service.getDetails({placeId: place_id}, function(result, status){
		if (status === google.maps.places.PlacesServiceStatus.OK){
			var origin = document.getElementById('origin');
			var destination = document.getElementById('destination');
			if (marked_places[place_id] === undefined){
				var option1 = document.createElement('option');
				option1.innerHTML = result.formatted_address;
				option1.value = result.formatted_address;
				option1.id = result.formatted_address;
				markers[place_id].setIcon('http://maps.google.com/mapfiles/kml/pal4/icon23.png');
				var option2 = option1.cloneNode(true);
				origin.appendChild(option1);
				destination.appendChild(option2);
				if (last_town_destination){
					destination.value = option2.value;
				}
				marked_places[result.place_id] = {address: result.formatted_address, location: result.geometry.location};
			} else {
				markers[place_id].setMap(null);
				delete marked_places[place_id];
				delete markers[place_id];
				origin.removeChild(document.getElementById(result.formatted_address));
				destination.removeChild(document.getElementById(result.formatted_address));
			}
			if (Object.keys(marked_places).length > 1 && live_road){
					findRoad();
			}
		}
	});
}

function infoCallback(result, status){
	if (status === google.maps.places.PlacesServiceStatus.OK){
		if (info_window !==undefined){
			info_window.close();
			delete info_window;
		}
		info_window = new google.maps.InfoWindow;
		info_window.setContent(result.formatted_address);
		info_window.open(map, markers[result.place_id]);
	}
}
 
function findRoad(){
	var waypts = [];
	var origin_address = document.getElementById('origin').value;
	var destination_address = document.getElementById('destination').value;
	for (place_id in marked_places){
		if (marked_places[place_id].address == origin_address){
			var origin = marked_places[place_id].location;
		} else {
			if (marked_places[place_id].address == destination_address){
				var destination = marked_places[place_id].location;
			} else {
				waypts.push({location: marked_places[place_id].location});
			}
		}
	}
	clearRoads();
	direction_service.route({
		origin: origin,
		destination: destination,
		waypoints: waypts,
		provideRouteAlternatives: true,
		travelMode: google.maps.TravelMode.DRIVING
	}, buildRoads);
	direction_service.route({
		origin: origin,
		destination: destination,
		waypoints: waypts,
		provideRouteAlternatives: true,
		optimizeWaypoints: true,
		travelMode: google.maps.TravelMode.DRIVING
	}, buildRoads);
}

function clearRoads(){
	roads.length = 0;
	roads_display.forEach(function(item){
		item.setMap(null);
	});
	roads_display.length = 0;
}

function swap(a, b){
	var c = a;
	a = b;
	b = c;
}
  
function buildRoads(result, status){
	var roads_length = roads.length;
	if (status === google.maps.DirectionsStatus.OK){
		var waypoints = [];
		result.geocoded_waypoints.forEach(function(waypoint_item){
			places_service.getDetails({placeId: waypoint_item.place_id}, function(waypoint, stat){
				if (stat == google.maps.places.PlacesServiceStatus.OK){
					waypoints.push({address: waypoint.formatted_address, position: waypoint.geometry.location});
				}
			});
		});
		result.routes.forEach(function(route_item, i){
			var distance = 0;
			var path = [];
			route_item.legs.forEach(function(leg_item){
				leg_item.steps.forEach(function(step_item){
					step_item.path.forEach(function(path_item){
						path.push(path_item);
					});
					distance += step_item.distance.value;
				});
			});
			var road_display = new google.maps.Polyline({
				map: map,
				strokeWeight: 5,
				strokeOpacity: 0.3,
				strokeColor: colors[roads.length],
				path: path
			});	
			road_display.addListener('click', function(){
				selectRoad(roads_length + i, road_display, waypoints)
			});			
			roads_display.push(road_display);
			roads.push({distance: distance, waypoints: waypoints, path: google.maps.geometry.encoding.encodePath(path)});
		});
	}
}

function selectRoad(index, road_display, waypoints){
	roads_display.forEach(function(road_display_item){
		road_display_item.setOptions({
			strokeOpacity: 0.3
		});
	});
	road_display.setOptions({
		strokeOpacity: 1.0
	});
	selected_road = index;
	ordered_markers.forEach(function(item){
		item.setMap(null);
	});
	ordered_markers.length = 0;
	waypoints.forEach(function(waypoint_item, i){
		var marker = new google.maps.Marker({
			map: map,
			position: waypoint_item.position,
			label: '' + (i + 1)
		});
		ordered_markers.push(marker);
	});	
}

function setLiveRoad(){
	if (live_road == false){
		live_road = true;
		document.getElementById('buildButton').disabled = true;
	} else {
		live_road = false;
		document.getElementById('buildButton').disabled = false;
	}
}

function setLastTownDestination(){
	if (last_town_destination == false){
		last_town_destination = true;
	} else {
		last_town_destination = false;
	}
}

function setNearestTownAdded(){
	if (nearest_town_added == false){
		nearest_town_added = true;
	} else {
		nearest_town_added = false;
	}
}

function clearSelectTag(elem){
	var elem_childs = elem.getElementsByTagName('*');
	var elem_childs_length = elem_childs.length;
	for (var i = elem_childs_length; i > 0; i--){
		elem_childs[i - 1].remove();
	}
}

function clearMap(){
	clearRoads();
	clearAllMarkers();
	clearSelectTag(document.getElementById('origin'));
	clearSelectTag(document.getElementById('destination'));
}

function sendRoad(){
	if (selected_road === undefined){
		alert("Wrong road selected!!!");
		return;
	}
	var str = JSON.stringify(roads[selected_road]);
	alert(str);
	//socket.send(str);
}