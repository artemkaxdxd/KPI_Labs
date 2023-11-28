import { Component, Input } from '@angular/core';
@Component({
  selector: 'my-app',
  template: `
  <div>
  <p valuesize [selectedSize]="selectedSize" [defaultSize]="'14px'">Hello Angular</p>
  <p>Angular представляє модульну архітектуру додатку</p>
  <p>Введіть розмір шрифта:<input [(ngModel)]="selectedSize" /></p>
  <p>Розмір шрифта зараз: {{selectedSize}}</p>
  </div>`
})
export class AppComponent {
  @Input() selectedSize = "12";
}