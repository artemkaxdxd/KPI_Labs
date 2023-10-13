import { Component, OnChanges, SimpleChanges } from '@angular/core';

@Component({
  selector: 'my-app',
  template: `<child-comp [name]="name"></child-comp>
 <input type="text" [(ngModel)]="name" />
 <input type="number" [(ngModel)]="age" />`
})
export class AppComponent implements OnChanges {
  name: string = "Tom";
  age: number = 25;
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