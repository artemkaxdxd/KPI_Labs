import { Component, Input, OnInit, OnDestroy, Output, EventEmitter } from '@angular/core';
import { Observable } from 'rxjs';
import { Post } from '../app.component';

@Component({
  selector: 'app-post',
  templateUrl: './post.component.html',
  styleUrls: ['./post.component.css']
})
export class PostComponent implements OnInit, OnDestroy {
  @Input(`toPost1`) myPost!: Post;
  @Output() onRemove = new EventEmitter<number>()
  date1!: Date
  title: string = '';
  text: string = '';
  myDate$: Observable<Date> = new Observable(obs => {
    setInterval(() => {
      obs.next(new Date())
    }, 1000)
  })

  constructor() { }
  removePost() {
    this.onRemove.emit(this.myPost.id)
  }
  ngOnInit(): void {
    this.myDate$.subscribe(date => {
      this.date1 = date
    })
  }


  ngOnDestroy() {
    console.log('метод ngOnDestroy');
  }
}
