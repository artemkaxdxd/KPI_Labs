import { Component } from '@angular/core';
@Component({
  selector: 'my-app',
  template: ` <div>
  <p bold>Вивчаю директиви</p>
  <p size [selectedSize]="newSize" [defaultSize]='"15px"'>Створення атрибутивних директив</p>
  <p>Введіть розмір шрифта:<input type="text" [(ngModel)]="newSize" /></p>
  </div>
  <div>
  <p italic>Вивчаю директиви</p>
  <p>Створення атрибутивних директив</p>
  </div>
  <div>
  <p mousebold>Робота з декоратором @HostListener</p>
  <p>Реагування на покажчик миші</p>
  </div>
  <div>
  <p mouseitalic>Робота з декоратором @HostListener</p>
  <p>Реагування на покажчик миші при допомозі @HostBinding</p>
  </div>
  <div>
  <p hostmousebold>Робота з декоратором @HostListener</p>
  <p>Реагування на покажчик миші при допомозі @HostBinding</p>
  </div>
`
})
export class AppComponent {
  selectedSize = "12";
  newSize = '';
}