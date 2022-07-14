#define TRIGGER_PIN 3
#define ECHO_PIN 2
#define LED_PIN LED_BUILTIN
#define DISTANCE_THRESHOLD_CM 15
#define BUCKET_COUNT_THRESHOLD 8

static int bucketCounter = 0;

void setup() {
	pinMode(TRIGGER_PIN, OUTPUT);
	pinMode(LED_PIN, OUTPUT);
	pinMode(ECHO_PIN, INPUT);
	Serial.begin(9600);
}

/**
 * Returns the truncated distance in centimeters
 * as given by an HC-SR04.
 */
int getDistance() {
	digitalWrite(TRIGGER_PIN, LOW);
	delayMicroseconds(2);
	digitalWrite(TRIGGER_PIN, HIGH);
	delayMicroseconds(10);
	digitalWrite(TRIGGER_PIN, LOW);
	return (pulseIn(ECHO_PIN, HIGH) * 0.034) / 2;
}

void loop() {
	int distance = getDistance();

	// Use bucketCounter as a little buffer for controlling false-positive
	// or false-negative sensory readings. Ensures the actuator is only
	// engaged after BUCKET_COUNT_THRESHOLD consistent read events occur.
	if (distance < DISTANCE_THRESHOLD_CM) {
		if (bucketCounter < BUCKET_COUNT_THRESHOLD)
			bucketCounter++;
	} else {
		if (bucketCounter > 0)
			bucketCounter--;
	}

	Serial.print("Distance: ");
	Serial.print(distance);
	Serial.print("cm, bucket counter: ");
	Serial.println(bucketCounter);

	// Turn the LED on whenever an object is DISTANCE_THRESHOLD_CM 
	// or less from the sensor.
	if (bucketCounter >= BUCKET_COUNT_THRESHOLD)
		digitalWrite(LED_PIN, HIGH);
	else if (bucketCounter <= 0)
		digitalWrite(LED_PIN, LOW);

	delayMicroseconds(10);
}
