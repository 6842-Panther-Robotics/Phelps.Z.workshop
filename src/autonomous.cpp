#include "main.h"

void redFront() {
  moveLift(3000);
}

void blueFront() {
  moveLift(1500);
}

void autonomous() {

  switch (autonIndex) {
    case 0:
      redFront();
      break;
    case 1:
      blueFront();
      break;
  }
}
