import { Directive, ElementRef, Renderer2 } from '@angular/core';
@Directive({
  selector: '[italic]'
})
export class ItalicDirective {
  constructor(private elementRef: ElementRef, private renderer: Renderer2) {
    this.renderer.setStyle(this.elementRef.nativeElement, "font-style", "italic");
  }
}