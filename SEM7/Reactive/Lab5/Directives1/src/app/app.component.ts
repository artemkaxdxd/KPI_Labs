import { Component } from '@angular/core';

@Component({
  selector: 'my-app',
  template: `
<div [ngClass]="{verdanaFont:isVerdana}">
<h1>Hello Angular</h1>
<p [ngClass]="{segoePrintFont:isSegoe}">
Angular представляє модульну архітектуру додатку
</p>
</div>
<div [ngClass]="currentClasses">
<h1>Hello Angular</h1>
<p>
Angular представляє модульну архітектуру додатку
</p>
</div>
<div [ngStyle]="{'font-size':'13px', 'font-family':'Verdana', 'color':'green'}">
<h1>Вивчаємо директиви</h1>
<p [ngStyle]="{'font-size':'16px', 'font-family':'Segoe Print'}">
Використання атрибутивної директиви [ngStyle]
</p>
</div>
 <div [ngClass]="{invisible: currentClasses.visibility}">
 <h1> Вивчаємо директиви </h1>
 <p>
 Використання динамічної зміни стилів
 </p>
 </div>
 <button (click)="currentClasses.toggle()">Toggle</button>`,
  styles: [`
.verdanaFont{font-size:15px; font-family:Verdana;}
.segoePrintFont{font-size:16px; font-family:"Segoe Print";}
.navyColor{color:navy;}
.invisible{display:none;}
`]
})
export class AppComponent {
  isVerdana = true;
  isSegoe = true;
  isNavy = true;
  currentClasses = {
    verdanaFont: this.isVerdana,
    navyColor: this.isNavy,
    visibility: true,
    toggle() {
      this.visibility = !this.visibility;
    }
  }
}