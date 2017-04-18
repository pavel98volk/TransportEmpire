var map;
var info_window;
var places_service;
var direction_service;
var selected_road;

var mouseover				 = false;
var live_road				 = true;
var last_town_destination	 = true;
var nearest_town_added		 = true;

var selected_places	 = {};
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
	places_service = new google.maps.places.PlacesService(map);
	direction_service = new google.maps.DirectionsService;
	info_window = new google.maps.InfoWindow;
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
		clearOrderedMarkers();
		createMarker(results[0]);
	}
}

function radarCallback(results, status){
	if (status === google.maps.places.PlacesServiceStatus.OK){
		clearMarkers();
		clearOrderedMarkers();
		results.forEach(function(result_item){
			createMarker(result_item);
		});
	}
}

function clearMarkers(){
	for (place_id in markers){
		if (selected_places[place_id] === undefined){
			markers[place_id].setMap(null);
			delete markers[place_id];
		}
	}
}

function createMarker(place){
	var marker_place = {location: place.geometry.location, placeId: place.place_id};
	if (markers[place.place_id] !== undefined){
		return;
	}
	var marker = new google.maps.Marker({
		place: marker_place,
		map: map,
		zIndex: 1
	});	
	marker.addListener('click', function(){
		addMarkerToRoad(marker);
	});
	marker.addListener('mouseover', function(){
		showInfoWindow(marker);	
		marker.setZIndex(2);
	});
	marker.addListener('mouseout', function(){
		hideInfoWindow();	
		marker.setZIndex(1);
	});
	if (nearest_town_added){
		addMarkerToRoad(marker);
	}
	markers[place.place_id] = marker;
}

function showInfoWindow(marker){
	mouseover = true;
	setTimeout(function(){
			if (mouseover){
				places_service.getDetails({placeId: marker.getPlace().placeId}, infoCallback);
				info_window.open(map, marker);
			}
		}, 600
	);
}

function hideInfoWindow(){
	mouseover = false;
	info_window.close();
}

function addMarkerToRoad(marker) {
	places_service.getDetails({placeId: marker.getPlace().placeId}, function(result, status){
		if (status === google.maps.places.PlacesServiceStatus.OK){
			var origin = document.getElementById('origin');
			var destination = document.getElementById('destination');
			if (selected_places[marker.getPlace().placeId] === undefined){
				var option1 = document.createElement('option');
				option1.innerHTML = result.formatted_address;
				option1.value = result.formatted_address;
				option1.id = result.formatted_address;
				var option2 = option1.cloneNode(true);
				origin.appendChild(option1);
				destination.appendChild(option2);
				if (last_town_destination){
					destination.value = option2.value;
				}
				marker.setIcon('http://maps.google.com/mapfiles/kml/pal4/icon23.png');
				selected_places[marker.getPlace().placeId] = {address: result.formatted_address, location: result.geometry.location};
			} else {
				marker.setMap(null);
				delete selected_places[marker.getPlace().placeId];
				delete marker;
				origin.removeChild(document.getElementById(result.formatted_address));
				destination.removeChild(document.getElementById(result.formatted_address));
			}
			if (Object.keys(selected_places).length > 1 && live_road){
					findRoad();
			}
		}
	});
}

function infoCallback(result, status){
	if (status === google.maps.places.PlacesServiceStatus.OK){
		info_window.setContent(result.formatted_address);
	}
}
 
function findRoad(){
	clearOrderedMarkers();
	var waypoints = [];
	var origin_address = document.getElementById('origin').value;
	var destination_address = document.getElementById('destination').value;
	for (place_id in selected_places){
		if (selected_places[place_id].address == origin_address){
			var origin = selected_places[place_id].location;
		} else {
			if (selected_places[place_id].address == destination_address){
				var destination = selected_places[place_id].location;
			} else {
				waypoints.push({location: selected_places[place_id].location});
			}
		}
	}
	clearRoads();
	direction_service.route({
		origin: origin,
		destination: destination,
		waypoints: waypoints,
		travelMode: google.maps.TravelMode.DRIVING,
		provideRouteAlternatives: true,
		optimizeWaypoints: true
	}, buildRoads);
	direction_service.route({
		origin: origin,
		destination: destination,
		waypoints: waypoints,
		travelMode: google.maps.TravelMode.DRIVING,
		provideRouteAlternatives: true
	}, buildRoads);
}

function clearRoads(){
	roads.length = 0;
	roads_display.forEach(function(display_item){
		display_item.setMap(null);
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
		result.routes.forEach(function(route_item, i){
			var waypoints = [];
			var distance = 0;
			var path = [];
			route_item.legs.forEach(function(leg_item){
				if (waypoints.length != 0){
					waypoints.pop();
				}
				waypoints.push({address: leg_item.start_address, location: leg_item.start_location});
				waypoints.push({address: leg_item.end_address, location: leg_item.end_location});
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

function clearOrderedMarkers(){
	ordered_markers.forEach(function(item){
		item.setMap(null);
	});
	ordered_markers.length = 0;
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
	clearOrderedMarkers();
	waypoints.forEach(function(waypoint_item, i){
		var marker = new google.maps.Marker({
			map: map,
			position: waypoint_item.location,
			label: '' + (i + 1),
			zIndex: 2
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

function clearAllMarkers(){
	for (place_id in markers){
		markers[place_id].setMap(null);
		delete markers[place_id];
		if (selected_places[place_id] !== undefined){
			delete selected_places[place_id];
		}
	}
}

function clearMap(){
	clearRoads();
	clearAllMarkers();
	clearOrderedMarkers();
	delete selected_places;
	selected_places = {};
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
	//var socket = new WebSocket("ws://10.1.3.121:1234");
	//socket.send(str);
}