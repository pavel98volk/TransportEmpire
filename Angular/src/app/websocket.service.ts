import { Injectable } from '@angular/core';

interface packet{
request:string;
resource:string;
data:any;
}
@Injectable()
export class WebsocketService {
  ws:WebSocket;
  pack:packet;
  open(url:string){
    this.ws = new WebSocket(url);
  }

  send(rqst: string,src:string,data_obj:any){
    this.pack={
        request:rqst,
        resource:src,
        data:data_obj
    }

    if(this.ws.OPEN){
      this.ws.send(JSON.stringify(this.pack));
    }
  }
  addRecieveFunc(func:any){
    this.ws.onmessage=func;
  }
  
  constructor() { }

}
