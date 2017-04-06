var map;
var mouseover;
var info_window;
var cities = {};
var markers = {};
var placesService;
var directionService;
var directionDisplay;

function initMap() {
	var position = {lat: 50.4501, lng: 30.523400000000038}; //Kiyv
	map = new google.maps.Map(document.getElementById('map'), {
		center: position,
		zoom: 8
	});
	map.addListener('click', function(event){
		searchNearestTownsWithFilters(event.latLng);
	});
	placesService = new google.maps.places.PlacesService(map);
	directionService = new google.maps.DirectionsService;
	directionDisplay = new google.maps.DirectionsRenderer;
	directionDisplay.setMap(map);
}

function searchNearestTownsWithFilters(click_position){
	//var filters = document.getElementById('filters');
	placesService.radarSearch({
		location: click_position,
		radius: 10000,
		types: ['locality']
	}, radarCallback);
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
		if (cities[place_id] === undefined){
			markers[place_id].setMap(null);
			delete markers[place_id];
		}
	}
}

function createMarker(place){
	if (markers[place.place_id] !== undefined)
		return;
	markers[place.place_id] = new google.maps.Marker({
		position: place.geometry.location,
		map: map,
		zIndex: 1
	});	
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
				placesService.getDetails({placeId: place_id}, infoCallback);
			}
		}, 600
	);
	markers[place_id].setZIndex(2);
}

function hideInfoWindow(place_id){
	mouseover = false;
	markers[place_id].setZIndex(1);
}

function addMarkerToRoad(place_id) {
	if (cities[place_id] === undefined){
		markers[place_id].setIcon('http://maps.google.com/mapfiles/kml/pal4/icon23.png');
		placesService.getDetails({placeId: place_id}, function(result, status){
			if (status === google.maps.places.PlacesServiceStatus.OK){
				cities[result.place_id] = {address: result.formatted_address, location: result.geometry.location};
				if (Object.keys(cities).length > 1){
					showRoute();
				}
			}
		});
	} else {
		delete cities[place_id];
		markers[place_id].setIcon('http://maps.google.com/mapfiles/kml/pal4/icon7.png');
		if (Object.keys(cities).length > 1){
			showRoute();
		}
	}
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
 
function showRoute(){
	var waypts = [];
	for (place_id in cities){
		waypts.push({location: cities[place_id].location});
	}
	directionService.route({
		origin: waypts.shift(),
		destination: waypts.pop(),
		waypoints: waypts,
		optimizeWaypoints: true,
		travelMode: google.maps.TravelMode.DRIVING
	}, displayRoute);
}

function displayRoute(result, status){
	if (status === google.maps.DirectionsStatus.OK){
		directionDisplay.setDirections(result);
	}	
}

function sendRoad(){
	var socket = new WebSocket("ws://10.1.3.121:1234");
	var str = JSON.stringify(cities);
	socket.send(str);
}