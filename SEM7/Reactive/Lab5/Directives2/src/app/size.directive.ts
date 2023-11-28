import { Directive, HostListener, Input, HostBinding } from '@angular/core';
@Directive({
  selector: '[size]'
})
export class SizeDirective {

  @Input() selectedSize = "18px";
  @Input() defaultSize = "16px";

  private fontSize: string;
  constructor() {
    this.fontSize = this.defaultSize;
  }
  @HostBinding("style.fontSize") get getFontSize() {
    return this.fontSize;
  }
  @HostBinding("style.cursor") get getCursor() {
    return "pointer";
  }
  @HostListener("mouseenter") onMouseEnter() {
    this.fontSize = this.selectedSize;
  }
  @HostListener("mouseleave") onMouseLeave() {
    this.fontSize = this.defaultSize;
  }
}