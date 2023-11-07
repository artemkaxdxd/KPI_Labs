import { Component, Input, OnInit, OnDestroy, Output, EventEmitter } from
  '@angular/core';
import { Post } from '../app.component';
14
@Component({
  selector: 'app-post',
  templateUrl: './post.component.html',
  styleUrls: ['./post.component.css']
})
export class PostComponent implements OnInit, OnDestroy {
  @Input(`toPost1`) myPost!: Post;
  @Output() onRemove = new EventEmitter<number>()
  constructor() { }
  removePost() {
    this.onRemove.emit(this.myPost.id)
  }
  ngOnInit(): void {
  }
  ngOnDestroy() {
    console.log('метод ngOnDestroy');
  }
}
