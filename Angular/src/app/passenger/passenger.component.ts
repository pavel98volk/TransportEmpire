import { Component, OnInit,Injectable } from '@angular/core';
import { WebsocketService} from '..//websocket.service';






declare function initMap();
declare function getRoute();
declare function setRoute(route:any);

@Component({
  selector: 'app-passenger',
  templateUrl: 'passenger.component.html',
  styleUrls: ['passenger.component.css'],
  
})
export class PassengerComponent implements OnInit {

  send():void{
  var a=getRoute();
  if(a)
  this.wsc.send("route",getRoute());
  else if(!confirm("select road"))alert("then no server for ya");
 }
 requestRoad(){
   this.wsc.send("give me road","");
 }
  showList(){};
    constructor(private wsc:WebsocketService) {
     
    }

  ngOnInit() {
    initMap(); 
  this.wsc.addRecieveFunc(function(ev:MessageEvent){var obj =JSON.parse(ev.data);if(obj.info == "route") setRoute(obj.data);});
  

  }

}
