void main() {
    print("Hello world");
    println("Hello world");
    print("Hello world");
    println("Hello world");

    datetime now();
    eprintln(
        now.get_day() + "."
        + now.get_month() + "."
        + now.get_year() + " "
        + now.get_hour() + ":"
        + now.get_minute() + ":"
        + now.get_second()
    );
    eprintln(sin(2 + 2) + " is the result.");

    Log::trace("catch me if you can");
    Log::debug("this has the least priority");
    Log::info("this is my log message");
    Log::warning("attention please, may I have you attention please?!");
    Log::warn("attention please, may I have you attention please?!");
    Log::error("may the real slim shady please stand up?! I repeat...");
    Log::critical("may the real slim shady please stand up?!");
}

int solve(double p, double q, double &out x1, double &out x2) {
    const double discriminant = (p / 2.0) * (p / 2.0) - q;
    if (discriminant < 0.0) {
        return 0;
    }
    if (discriminant == 0.0) {
        x1 = -p / 2.0;
        return 1;
    }
    x1 = -p / 2.0 + sqrt(discriminant);
    x2 = -p / 2.0 - sqrt(discriminant);
    return 2;
}

int add(int a, int b) {
    return a + b;
}

uint test(const string &in text) {
    eprintln("Hello, world!");
    eprintln("This is AngelScript saying 'hello!', " + text);
    return text.length();
}

uint64 num_player_instances = 0;

class Player {
    uint64 countdown = 0;
    int kind = 0;

    Player() {
        ++num_player_instances;
        Log::warning("this is instance #" + num_player_instances);
        kind = num_player_instances % 2;
        reset_countdown();
    }

    void reset_countdown() {
        if (kind == 0) {
            countdown = 100000;
        } else {
            countdown = 50000;
        }
    }

    void awake() {
        Log::critical("rise and shine!");
    }

    void update() {
        --countdown;
        if (countdown == 0) {
            reset_countdown();
            if (kind == 0) {
                Log::info("countdown reset");
            } else {
                Log::warning("countdown reset");
            }
        }
    }
}
