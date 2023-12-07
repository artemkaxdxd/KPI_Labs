import { Pipe, PipeTransform } from '@angular/core';
@Pipe({
  name: 'join',
  pure: false
})
export class JoinPipe implements PipeTransform {
  transform(array: any, start?: any, end?: any): any {
    return array.join(", ");
  }
}