import { Component } from '@angular/core';

@Component({
  selector: 'my-app',
  template: `
 <h2>Кількість кліків: {{clicks}}</h2>
 <child-comp (onChanged)="onChanged($event)"></child-comp>
`
})
export class AppComponent {
  name: string = "Tom";
  age: number = 24;
  clicks: number = 0;
  onChanged(increased: any) {
    increased == true ? this.clicks++ : this.clicks--;
  }
}