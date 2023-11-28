import { Directive, Input, TemplateRef, ViewContainerRef } from '@angular/core';

@Directive({
  selector: '[sum]'
})

export class SumDirective {
  val1 = 0;
  val2 = 0;
  @Input() set sumFrom(value: number) {
    this.val1 = value;
  }
  @Input() set sumAnd(value: number) {
    this.val2 = value;
    const result = this.val1 + this.val2;
    // Use the ViewContainerRef to create an embedded view
    this.viewContainer.createEmbeddedView(this.templateRef, {
      $implicit:
        result
    });
  }
  constructor(
    private templateRef: TemplateRef<any>,
    private viewContainer: ViewContainerRef
  ) { }
}