#ifndef VERSIONCHECKER_H_
#define VERSIONCHECKER_H_

#include <curl/curl.h>
#include "json.hpp"

#include "Config/Version.h"
#include "../Utils/Logging.h"
#include "../Utils/VersionCompare.h"

using json = nlohmann::json;

//* GitVersion
/**
 * \brief Contains information about a Git release (version).
 */
struct GitVersion
{
    std::string Repository; /**< \brief Name of the GitHub repository. */
    std::string Tag;        /**< \brief Tag version. */
    std::string Name;       /**< \brief Tag name (description). */
    std::string Commit;     /**< \brief SHA commit. */
    bool PreRelease;        /**< \brief Is pre-release?. */
};

//* VersionChecker
/**
 * \brief Checks Mania++ version (and possibly plugin versions).
 */
class VersionChecker
{
public:
    /*!
     * \brief Returns whether there are updates available.
     *
     * \param repository     Name of the GitHub repository.
     * \param currentVersion Version to which the repository to.
     */
    bool CheckForUpdates(std::string repository, std::string currentVersion);

private:
    /*!
     * \brief Receives data from cURL input.
     *
     * \param contents       Contents from cURL.
     * \param size           Size of contents.
     * \param nmemb          Number of members (?).
     * \param tags           Output string.
     */
    static size_t receiveData(void* contents, size_t size, size_t nmemb, std::string* tags);

    /*!
     * \brief Retrieves data via cURL.
     *
     * \param url            URL to retrieve.
     * \param data           Received data (return).
     */
    void retrieveData(std::string url, std::string* data);

    /*!
     * \brief Retrieves versions (tags) of repository.
     *
     * \param repository     Repository name.
     */
    std::vector<GitVersion> retrieveVersions(std::string repository);

    /*!
     * \brief Decodes the JSON response with versions (tags) of repository.
     *
     * \param response       Server response (JSON).
     */
    std::vector<GitVersion> decodeVersions(std::string response);

    /*!
     * \brief Retrieves release information.
     *
     * \param version        Version struct.
     */
    void retrieveRelease(GitVersion* version);

    /*!
     * \brief Decodes the JSON response with release and inputs info into version struct.
     *
     * \param version        Version struct.
     * \param response       Server response (JSON).
     */
    void decodeRelease(GitVersion* version, std::string response);
};

#endif // VERSIONCHECKER_H_
