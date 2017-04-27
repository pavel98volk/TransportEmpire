import { Component } from '@angular/core';
import { WebsocketService} from './/websocket.service';

@Component({
  selector: 'app-root',
  templateUrl: './app.component.html',
  styleUrls: ['./app.component.css']
})
export class AppComponent {
  title = 'app works!';
  constructor(private wsc:WebsocketService) {
  wsc.open("ws://localhost:8080");
 
    }

}
