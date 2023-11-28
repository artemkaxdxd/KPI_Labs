import { Directive, HostListener, HostBinding } from '@angular/core';
@Directive({
  selector: '[mouseitalic]'
})
export class MouseitalicDirective {
  private fontStyle = "normal";
  @HostBinding("style.font-style") get getFontStyle() {
    return this.fontStyle;
  }
  @HostBinding("style.cursor") get getCursor() {
    return "pointer";
  }
  @HostListener("mouseenter") onMouseEnter() {
    this.fontStyle = "italic";
  }
  @HostListener("mouseleave") onMouseLeave() {
    this.fontStyle = "normal";
  }
}
