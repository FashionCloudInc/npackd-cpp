#ifndef REPOSITORYXMLHANDLER_H
#define REPOSITORYXMLHANDLER_H

#include <QXmlDefaultHandler>
#include <QString>
#include <QXmlAttributes>

#include "license.h"
#include "package.h"
#include "packageversion.h"
#include "abstractrepository.h"
#include "dbrepository.h"

/**
 * @brief SAX handler for the repository XML.
 */
class RepositoryXMLHandler: public QXmlDefaultHandler
{
    enum WHERE {
        TAG_VERSION,
        TAG_VERSION_IMPORTANT_FILE,
        TAG_VERSION_CMD_FILE,
        TAG_VERSION_FILE,
        TAG_VERSION_DEPENDENCY,
        TAG_VERSION_DETECT_FILE,
        TAG_PACKAGE,
        TAG_PACKAGE_CHANGELOG,
        TAG_LICENSE,
        TAG_VERSION_URL,
        TAG_VERSION_SHA1,
        TAG_VERSION_HASH_SUM,
        TAG_VERSION_DETECT_MSI,
        TAG_VERSION_DEPENDENCY_VARIABLE,
        TAG_VERSION_DETECT_FILE_PATH,
        TAG_VERSION_DETECT_FILE_SHA1,
        TAG_PACKAGE_TITLE,
        TAG_PACKAGE_URL,
        TAG_PACKAGE_DESCRIPTION,
        TAG_PACKAGE_ICON,
        TAG_PACKAGE_LICENSE,
        TAG_PACKAGE_CATEGORY,
        TAG_PACKAGE_TAG,
        TAG_PACKAGE_STARS,
        TAG_PACKAGE_LINK,
        TAG_LICENSE_TITLE,
        TAG_LICENSE_URL,
        TAG_LICENSE_DESCRIPTION,
        TAG_SPEC_VERSION
    };

    AbstractRepository* rep;

    License* lic;
    Package* p;
    PackageVersion* pv;
    PackageVersionFile* pvf;
    Dependency* dep;

    QString chars;
    QString error;
    QStringList tags;

    QUrl url;

    int findWhere();
public:
    /**
     * -
     *
     * @param rep [move] data will be stored here
     * @param url this value will be used for resolving relative URLs. This can
     *     be an empty URL. In this case relative URLs are not allowed.
     */
    RepositoryXMLHandler(AbstractRepository* rep, const QUrl& url);

    virtual ~RepositoryXMLHandler();

    /**
     * @brief enters a tag without it being visible in the XML. This method
     * can be used to parse top level <version> tags.
     *
     * @param qName the name of the tag
     */
    void enter(const QString& qName);

    bool startElement(const QString& namespaceURI,
            const QString& localName, const QString& qName,
            const QXmlAttributes& atts);
    bool endElement(const QString& namespaceURI,
            const QString& localName, const QString& qName);
    bool characters(const QString& ch);
    bool fatalError(const QXmlParseException& exception);
    QString errorString() const;
};

#endif // REPOSITORYXMLHANDLER_H
