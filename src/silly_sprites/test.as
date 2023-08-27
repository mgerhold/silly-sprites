class Player {
    private double next_log_time = 0.0;

    void awake() {
        Log::critical("rise and shine!");
    }

    void update(Time time) {
        if (next_log_time == 0.0) {
            next_log_time = time.elapsed + 0.5;
        }

        if (time.elapsed >= next_log_time) {
            Log::info("waiting for time to pass by...");
            next_log_time = time.elapsed + 0.5;
        }

        if (time.elapsed >= 2.0) {
            Log::info("destroying game object");
            destroy();
        }
    }
}
