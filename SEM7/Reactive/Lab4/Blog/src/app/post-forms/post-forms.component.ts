import { Component, EventEmitter, OnInit, Output } from '@angular/core';
import { Post } from '../app.component';
@Component({
  selector: 'app-post-form',
  templateUrl: './post-forms.component.html',
  styleUrls: ['./post-forms.component.css']
})
export class PostFormComponent implements OnInit {
  @Output() onAdd: EventEmitter<Post> = new EventEmitter<Post>()
  title = '';
  text = '';
  constructor() { }
  ngOnInit(): void {
  }
  addPost() {
    if (this.title.trim() && this.text.trim()) {
      const post: Post = {
        title: this.title,
        text: this.text
      }
      this.onAdd.emit(post);
      console.log('New post', post);
      this.title = this.text = '';
    }
  }
}
