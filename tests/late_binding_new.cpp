// expect-success
/*
 * Copyright 2014 Google Inc. All rights reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 *     http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <fruit/fruit.h>
#include "test_macros.h"

using fruit::Component;
using fruit::Injector;

struct X {
  INJECT(X()) = default;
};

struct Y {
  INJECT(Y()) {
    Assert(!constructed);
    constructed = true;
  }
  
  static bool constructed;
};

bool Y::constructed = false;

struct Z {
  INJECT(Z()) = default;
};

fruit::Component<Z, Y, X> getComponent() {
  return fruit::createComponent();
}

int main() {
  
  fruit::NormalizedComponent<> normalizedComponent(fruit::createComponent());
  Injector<Y> injector(normalizedComponent, getComponent());
  
  Assert(!Y::constructed);
  injector.get<Y>();
  Assert(Y::constructed);
  
  return 0;
}
