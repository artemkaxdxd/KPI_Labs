import { NgModule } from '@angular/core';
import { BrowserModule } from '@angular/platform-browser';
import { AppComponent } from './app.component';
import { FormatPipe } from './format.pipe';
import { JoinPipe } from './join.pipe';
import { SqrtPipe } from './sqrt.pipe';
@NgModule({
  imports: [BrowserModule],
  declarations: [AppComponent, FormatPipe, JoinPipe, SqrtPipe],
  bootstrap: [AppComponent]
})
export class AppModule { }