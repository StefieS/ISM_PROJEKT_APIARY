#ifndef __ONE_TROLLEY_GETTER
#define __ONE_TROLLEY_GETTER

class OneTrolleyGetter : public ITransportGetter {

public:
    OneTrolleyGetter(int capacity)
        : Trolley("Trolley", capacity),
          location(Location::Hives),
          status(TransportStatus::ReadyToLoad) {}

    bool transportAvailableForLoad(Location location) override;
    bool transportAvailableForUnload(Location location) override;

    void loadIntoTransport(Entity* caller) override;
    void unloadFromTransport() override;

    void moveToLocation(Location l) override;

private:
    Store Trolley;
    Location location;
    TransportStatus status;
};

#endif // __ONE_TROLLEY_GETTER