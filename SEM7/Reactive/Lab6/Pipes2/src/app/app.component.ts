import { Component } from '@angular/core';
import { Observable, interval } from 'rxjs';
import { map } from 'rxjs/operators';

@Component({
  selector: 'my-app',
  template: `
<input [(ngModel)]="num" name="fact">
<div>Результат: {{num | format}}</div>
<hr/>
<input #user name="user" class="form-control">
<button class="btn" (click)="users.push(user.value)">Add</button>
<p>{{users | join}}</p>
 <p>Модель: {{ phone| async }}</p>
 <button (click)="showPhones()">Посмотреть модели</button>`
})
export class AppComponent {
  num: number = 15.45;
  users = ["Tom", "Alice", "Sam", "Kate", "Bob"];
  phones = ["iPhone 7", "LG G 5", "Honor 9", "Idol S4", "Nexus 6P"];
  phone: Observable<string> | undefined;
  constructor() { this.showPhones(); }
  showPhones() {
    this.phone = interval(500).pipe(map((i: number) => this.phones[i]));
  }
}