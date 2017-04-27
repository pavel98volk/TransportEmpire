import { Component, OnInit } from '@angular/core';






@Component({
  selector: 'app-desktop',
  templateUrl: './desktop.component.html',
  styleUrls: ['./desktop.component.css']
})
export class DesktopComponent implements OnInit {
showmap:string="greetings";
goto_map():void{
  this.showmap="map";
}

  constructor() { 

  }

  ngOnInit() {
  }
}
