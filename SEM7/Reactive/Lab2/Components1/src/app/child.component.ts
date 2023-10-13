import { Input, Component } from '@angular/core';

@Component({
  selector: 'child-comp',
  template: `<ng-content></ng-content>
 <p>Привіт {{name}}</p>
 <p>Ім’я користувача: {{userName}}</p>
 <p>Вік користувача: {{userAge}}</p>`,
  styles: [`h2, p {color:red;}`]
})
export class ChildComponent {
  name = 'Тарас';
  @Input() userName: string = "";
  @Input() userAge: number = 24;
}