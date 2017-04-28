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

tab:number=1;



 send():void{
    var a=getRoute();
    if(a)
      this.wsc.send("POST","route",getRoute());
    else if(!confirm("select road"))alert("then no server for ya");
 }
 requestRoad(){
    this.wsc.send("GET","give me road","");
 }
  showList(){};
    constructor(private wsc:WebsocketService) {  
    }

  ngOnInit() {
    initMap(); 
  this.wsc.addRecieveFunc(function(ev:MessageEvent){var obj =JSON.parse(ev.data);if(obj.resource == "route") setRoute(obj.data);});
  

  }

}
