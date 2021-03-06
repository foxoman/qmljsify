#ifndef QMLJSIFY_H
#define QMLJSIFY_H

#include <QString>

class Qmljsify
{
public:
    Qmljsify();

    QString buildFolder() const;

    void setBuildFolder(const QString &buildFolder);

    QString package() const;

    void setPackage(const QString &package);

    void prepare();

    void fetch();

    void build();

    /// Create a wrapper of compiled JavaScript
    void create();

    bool minifyEnabled() const;

    void setMinifyEnabled(bool minifyEnabled);

    QString createdJavaScriptFile() const;
    void setCreatedJavaScriptFile(const QString &createdJavaScriptFile);

    QString outputFolder() const;
    void setOutputFolder(const QString &outputFolder);

private:
    QString m_buildFolder;

    QString m_package;

    QString m_outputFolder;

    bool m_minifyEnabled;
};

#endif // QMLJSIFY_H
