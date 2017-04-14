var map;
var mouseover;
var live_road = false;
var last_town_destination = true;
var nearest_town_added = true;
var info_window;
var marked_places = {};
var markers = {};
var places_service;
var direction_service;
var direction_display = [];
var color_alphabet = '0123456789ABCDEF';

function initMap() {
	var position = {lat: 50.4501, lng: 30.523400000000038}; //Kiyv
	map = new google.maps.Map(document.getElementById('map'), {
		center: position,
		zoom: 8
	});
	map.addListener('click', function(event){
		searchNearestTownsWithFilters(event.latLng);
	});
	//var socket = new WebSocket("ws://10.1.3.121:1234");
	places_service = new google.maps.places.PlacesService(map);
	direction_service = new google.maps.DirectionsService;
}

function searchNearestTownsWithFilters(click_position){
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
		for (i in results){
			createMarker(results[i]);
		}
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
					buildRoad();
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
 
function buildRoad(){
	clearRoute();
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
	direction_service.route({
		origin: origin,
		destination: destination,
		waypoints: waypts,
		provideRouteAlternatives: true,
		travelMode: google.maps.TravelMode.DRIVING
	}, displayRoute);
	direction_service.route({
		origin: origin,
		destination: destination,
		waypoints: waypts,
		optimizeWaypoints: true,
		travelMode: google.maps.TravelMode.DRIVING
	}, displayRoute);
}

function clearRoute(){
	for (var i = direction_display.length; i > 0 ; i--){
		direction_display[i - 1].setMap(null);
		direction_display.pop();
	}
}

function displayRoute(result, status){
	var color_shift = direction_display.length;
	if (status === google.maps.DirectionsStatus.OK){
		for (var i = 0; i < result.routes.length; i++){
			var color_mix = i + 1 + color_shift * 5;
			var color = '#' + color_alphabet[(color_mix * 1) % 16] + color_alphabet[(color_mix * 11) % 16] + color_alphabet[(color_mix * 2) % 16] + color_alphabet[(color_mix * 7) % 16] + color_alphabet[(color_mix * 3) % 16] + color_alphabet[(color_mix * 5) % 16];					
			direction_display[direction_display.length] = new google.maps.Polyline({
				map: map,
				strokeWeight: 3,
				strokeOpacity: 1.0,
				strokeColor: color,
				path: result.routes[i].overview_path
			});		
		}
	}
}

function changeLiveRoad(){
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
	var length = elem_childs.length;
	for (var i = length; i > 0; i--){
		elem_childs[i - 1].remove();
	}
}

function clearMap(){
	clearRoute();
	clearAllMarkers();
	clearSelectTag(document.getElementById('origin'));
	clearSelectTag(document.getElementById('destination'));
}

function sendRoad(){
	var path = [];
	for (place_id in marked_places){
		path.push({address: marked_places[place_id].address, location: marked_places[place_id].location});
	}
	var str = JSON.stringify(path);
	alert(str);
	//socket.send(str);
}