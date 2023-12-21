import { NgModule } from '@angular/core';
import { BrowserModule } from '@angular/platform-browser';
import { FormsModule } from '@angular/forms';
import { AppComponent } from './app.component';
import { DataComponent } from './data.component';
import { DataService } from './data.service';
import { LogService } from './log.service';
@NgModule({
  imports: [BrowserModule, FormsModule],
  declarations: [AppComponent, DataComponent],
  providers: [DataService, LogService], // реєстрація сервісів
  bootstrap: [AppComponent, DataComponent]
})

export class AppModule { }