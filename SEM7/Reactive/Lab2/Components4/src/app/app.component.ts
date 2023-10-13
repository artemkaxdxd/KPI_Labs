import { Component, OnInit, OnDestroy } from '@angular/core';

@Component({
  selector: 'my-app',
  template: `<p>Hello Angular 2</p>`
})
export class AppComponent implements OnInit, OnDestroy {
  name: string = "Tom";

  constructor() { this.log(`constructor`); }
  ngOnInit() { this.log(`onInit`); }
  ngOnDestroy() { this.log(`onDestroy`); }
  private log(msg: string) {
    console.log(msg);
  }
}