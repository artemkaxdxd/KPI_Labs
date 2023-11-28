import { Directive, ElementRef, Renderer2, HostListener } from '@angular/core';
@Directive({
  selector: '[mousebold]'
})
export class MouseboldDirective {
  constructor(private element: ElementRef, private renderer: Renderer2) {
    this.renderer.setStyle(this.element.nativeElement, "cursor", "pointer");
  }
  @HostListener("mouseenter") onMouseEnter() {
    this.setFontWeight("bold");
  }
  @HostListener("mouseleave") onMouseLeave() {
    this.setFontWeight("normal");
  }
  private setFontWeight(val: string) {
    13
    this.renderer.setStyle(this.element.nativeElement, "font-weight", val);
  }
}
