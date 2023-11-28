import { Directive, ElementRef, Renderer2 } from '@angular/core';
@Directive({
  selector: '[hostmousebold]',
  host: {
    '(mouseenter)': 'onMouseEnter()',
    '(mouseleave)': 'onMouseLeave()'
  }
})
export class HostmouseboldDirective {
  constructor(private element: ElementRef, private renderer: Renderer2) {
    this.renderer.setStyle(this.element.nativeElement, "cursor", "pointer");
  }
  onMouseEnter() {
    this.setFontWeight("bold");
  }
  onMouseLeave() {
    this.setFontWeight("normal");
  }
  private setFontWeight(val: string) {
    this.renderer.setStyle(this.element.nativeElement, "font-weight", val);
  }
}
