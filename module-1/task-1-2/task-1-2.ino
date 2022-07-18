#define SWITCH_PIN 2
#define LED_PIN LED_BUILTIN

static int switchState = LOW;

void setup() {
	pinMode(SWITCH_PIN, INPUT_PULLUP);
	pinMode(LED_PIN, OUTPUT);
	attachInterrupt(digitalPinToInterrupt(SWITCH_PIN), onSwitchInterrupt, FALLING);
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

	Serial.println("Interrupt received");
	Serial.print("Turning the light ");
	Serial.println(switchState == HIGH ? "on" : "off");
}
