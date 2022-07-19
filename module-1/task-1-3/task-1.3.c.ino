#define SWITCH_PIN 2
#define SECOND_SWITCH_PIN 3
#define LED_PIN LED_BUILTIN
#define SECOND_LED_PIN 7

volatile static int switchState = LOW;
volatile static int secondSwitchState = LOW;

void setup() {
	pinMode(SWITCH_PIN, INPUT_PULLUP);
	pinMode(SECOND_SWITCH_PIN, INPUT_PULLUP);
	pinMode(LED_PIN, OUTPUT);
	pinMode(SECOND_LED_PIN, OUTPUT);
	attachInterrupt(digitalPinToInterrupt(SWITCH_PIN), onSwitchInterrupt, FALLING);
	attachInterrupt(digitalPinToInterrupt(SECOND_SWITCH_PIN), onSecondSwitchInterrupt, FALLING);
	Serial.begin(9600);
}

void loop() {
	Serial.println("Loop...");
	// Sleeping for one second at a time doesn't matter
	// since we can rely on an interrupt signal from the processor!
	delay(1000);
}

void onSwitchInterrupt() {
	// Enter critical section
	noInterrupts();
	switchState = !switchState;
	digitalWrite(LED_PIN, switchState);
	interrupts();
	// Exit critical section

	Serial.println("Interrupt received on first switch");
	Serial.print("Turning the first light ");
	Serial.println(switchState == HIGH ? "on" : "off");
}

void onSecondSwitchInterrupt() {
	// Enter critical section
	noInterrupts();
	secondSwitchState = !secondSwitchState;
	digitalWrite(SECOND_LED_PIN, secondSwitchState);
	interrupts();
	// Exit critical section

	Serial.println("Interrupt received on second switch");
	Serial.print("Turning the second light ");
	Serial.println(secondSwitchState == HIGH ? "on" : "off");
}

