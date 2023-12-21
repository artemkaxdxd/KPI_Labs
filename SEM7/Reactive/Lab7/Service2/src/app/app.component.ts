import { Component } from '@angular/core';
import { AppCounterService } from './services/app-counter.service';
import { LocalCounterService } from './services/local-counter.service';

@Component({
  selector: 'app-root',
  templateUrl: './app.component.html',
  providers: [LocalCounterService] // Реєстрація локального сервісу
})
export class AppComponent {
  constructor(public appCounterService: AppCounterService, public localCounterService: LocalCounterService) { }
}