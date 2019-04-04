#include <Arduino.h>
#include <mpspiffs.hpp>

void mount(const char * partition)
{
    Serial.printf("Mounting %s... ", partition);
    if(Spiffs.begin(partition, true))
    {
        Serial.println("success.");
    }
    else
    {
        Serial.println("failed.");
    }
}

void printSize()
{
    uint32_t total, used;
    Spiffs.getSize(total, used);
    Serial.printf(
        "Partition %s: 0x%x of 0x%x bytes used.\n",
        Spiffs.mountedPartition(), 
        used, 
        total);
}

void readFile(const char * path)
{
    auto file = Spiffs.open(path);
    if(file)
    {
        Serial.printf("Contents of %s: %s\n", path, file.readString().c_str());
        file.close();
    }
    else
    {
        Serial.printf("Could not open %s for reading.\n", path);
    }
}

void countUp(const char * path)
{
    auto file = Spiffs.open(path);
    if(!file)
    {
        Serial.printf("Could not open %s for reading.\n", path);
        return;
    }
    auto text = file.readString();
    file.close();

    auto oldValue = text.toInt();
    auto newValue = oldValue + 1;

    file = Spiffs.open(path, FILE_WRITE);
    if(!file)
    {
        Serial.printf("Could not open %s for writing.\n", path);
        return;
    }
    file.print(newValue);
    file.close();
    Serial.printf("Updated content of %s from %li to %li.\n", path, oldValue, newValue);
}

void unmount()
{
    Serial.printf("Unmounting %s... ", Spiffs.mountedPartition());
    if(Spiffs.end())
    {
        Serial.println("success.");
    }
    else
    {
        Serial.println("failed.");
    }
}

void setup()
{
    Serial.begin(115200);

    delay(1000);

    mount("first");
    printSize();
    readFile("/written.txt");
    countUp("/written.txt");
    unmount();

    mount("second");
    printSize();
    readFile("/uploaded.txt");
    unmount();
}

void loop()
{
    delay(10000);
}
