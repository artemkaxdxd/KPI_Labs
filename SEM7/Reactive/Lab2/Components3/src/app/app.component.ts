import { Component } from '@angular/core';

@Component({
  selector: 'my-app',
  template: `<child-comp [(userName)]="name"></child-comp>
 <div>Обране ім’я: {{name}}</div>`
})
export class AppComponent {
  name: string = "Tom";
}