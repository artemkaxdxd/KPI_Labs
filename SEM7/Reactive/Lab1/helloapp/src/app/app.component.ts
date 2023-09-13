import { Component } from '@angular/core';

@Component({
  selector: 'my-app',
  template: `<label>Введіть назву:</label>
<input [(ngModel)]="name" placeholder="name">
<h1>Ласкаво просимо {{name}}!</h1>`
})

export class AppComponent {
  name = ' ';
}