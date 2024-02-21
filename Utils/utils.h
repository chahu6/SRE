#ifndef UTILS_H
#define UTILS_H

#include <chrono>
#include <QDir>

struct Utils
{
    static int64_t getCurTimestamp()
    {
        return std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::system_clock::now().time_since_epoch())
            .count();
    }

    static bool mkDirs(QString dirPath)
    {
        QDir dir(dirPath);
        if(dir.exists())
        {
            return true;
        }
        else
        {
            bool result = dir.mkpath(dirPath);
            return result;
        }
    }
};

#endif // UTILS_H
