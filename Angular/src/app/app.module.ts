import { BrowserModule } from '@angular/platform-browser';
import { NgModule } from '@angular/core';
import { FormsModule } from '@angular/forms';
import { HttpModule } from '@angular/http';

import { AppComponent } from './app.component';
import { DesktopComponent } from './desktop/desktop.component';
import { PassengerComponent } from './passenger/passenger.component';
import { WebsocketService} from './websocket.service';


@NgModule({
  declarations: [
    AppComponent,
    DesktopComponent,
    PassengerComponent
  ],
  imports: [
    BrowserModule,
    FormsModule,
    HttpModule
  ],
  providers: [
    WebsocketService
  ],
  bootstrap: [AppComponent]
})
export class AppModule { }
