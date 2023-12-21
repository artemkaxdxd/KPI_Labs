import { Injectable, Optional } from '@angular/core'
import { Phone } from './phone'
import { LogService } from './log.service'

@Injectable()
export class DataService {
  private data: Phone[] = [
    { name: 'Apple iPhone 7', price: 36000 },
    { name: 'HP Elite x3', price: 38000 },
    { name: 'Alcatel Idol S4', price: 12000 },
  ]
  constructor(@Optional() private logService: LogService) { }
  getData(): Phone[] {
    // this.logService.write('операція отримання даних')
    if (this.logService)
      this.logService.write('операція отримання даних')
    return this.data
  }
  addData(name: string, price: number) {
    this.data.push(new Phone(name, price))
    this.logService.write('операція додавання даних')
  }
}
