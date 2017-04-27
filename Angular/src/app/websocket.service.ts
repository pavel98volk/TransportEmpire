import { Injectable } from '@angular/core';

interface packet{
request:string;
data:any;
}
@Injectable()
export class WebsocketService {
  ws:WebSocket;
  pack:packet;
  reciever:any=undefined;
  open(url:string){
    this.ws = new WebSocket(url);
  }

  send(rqst: string ,data_obj:any){
    this.pack={
        request:rqst,
        data:data_obj
    }

    if(this.ws.OPEN){
      this.ws.send(JSON.stringify(this.pack));
    }
  }
  addRecieveFunc(func:any){
   this.reciever=func;
    this.ws.onmessage=this.reciever;
  }
  
  constructor() { }

}
