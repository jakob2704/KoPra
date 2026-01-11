class FireControl{

  public: 
    void    Zielerfassung(TOF_sensor sensor, Turm_servo servo);
    void    Feuern(short firingAngle);
    uint_16_t calculateFiringAngle(uint_16_t distance; uint_8_t phi; uint_16_t muzzle_vel)
  private:
    void    sprayNPray(short* firingAngle);

}