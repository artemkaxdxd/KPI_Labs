import { Component, Input, OnInit, OnChanges, SimpleChanges } from
  '@angular/core';

@Component({
  selector: 'child-comp',
  template: `<p>Привіт {{name}}</p>`
})
export class ChildComponent implements OnInit, OnChanges {
  @Input() name: string = "";
  constructor() { this.log(`constructor`); }
  ngOnInit() { this.log(`onInit`); }

  ngOnChanges(changes: SimpleChanges) {
    for (let propName in changes) {
      let chng = changes[propName];
      let cur = JSON.stringify(chng.currentValue);
      let prev = JSON.stringify(chng.previousValue);
      this.log(`${propName}: currentValue = ${cur}, previousValue = ${prev}`);
    }
  }
  private log(msg: string) {
    console.log(msg);
  }
}