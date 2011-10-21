<?php

/**
 * Class definition for DSpace Parser.
 *
 * Parses DSpace REST API feed.
 */
class FeedsDSpaceParser extends FeedsParser {

  /**
   * Implements FeedsParser::parse().
   */
  public function parse(FeedsSource $source, FeedsFetcherResult $fetcher_result) {
    $xml = new SimpleXMLElement($fetcher_result->getRaw());
    $result = new FeedsParserResult();

    foreach ($xml->items->itementity as $item) {
      // GUID
      $items['guid'] = (string) $item->handle;

      // ID
      $items['id'] = (string) $item->id;

      // Last Modified
      $items['lastmodified'] = (string) $item->lastModified;

      // Title
      $items['title'] = (string) $item->name;

      // Submitter
      $items['submitter'] = (string) $item->submitter->netId;

      // Metadata
      $metadata = (string) $item->metadata;
      $metadata = simplexml_load_string("<metadata>" . $metadata . "</metadata>");

      // URL
      $url = $metadata->xpath('/metadata/meta[@name = "DC.identifier"]/@content');
      $items['url'] = (string) $url[0]->content;

      // Creators
      $creators = $metadata->xpath('/metadata/meta[@name = "DC.creator"]/@content');
      foreach ($creators as $creator) {
        $items['creators'][] = (string) $creator;
      }

      // Keywords
      $keywords = $metadata->xpath('/metadata/meta[@name = "DC.subject"]/@content');
      foreach ($keywords as $keyword) {
        $items['keywords'][] = (string) $keyword;
      }

      // Abstract
      $abstract = $metadata->xpath('/metadata/meta[@name = "DCTERMS.abstract"]/@content');
      $items['abstract'] = (string) $abstract[0]->content;

      //dvm($items);
      $result->items[] = $items;
      unset($items);
    }

    return $result;
  }

  /**
   * Implements FeedsParser::getMappingSources().
   */
  public function getMappingSources() {
    return array(
      'guid' => array(
        'name' => t('GUID'),
        'description' => t('Global Unique Identifier of the feed item.'),
      ),
      'id' => array(
        'name' => t('ID'),
        'description' => t('Identifier of the feed item.'),
      ),
      'lastmodified' => array(
        'name' => t('Last Modified'),
        'description' => t('Last Modified of the feed item.'),
      ),
      'title' => array(
        'name' => t('Title'),
        'description' => t('Title of the feed item.'),
      ),
      'abstract' => array(
        'name' => t('Abstract'),
        'description' => t('Abstract of the feed item.'),
      ),
      'submitter' => array(
        'name' => t('Submitter'),
        'description' => t('Submitter of the feed item.'),
      ),
      'url' => array(
        'name' => t('URL'),
        'description' => t('URL of the feed item.'),
      ),
      'creators' => array(
        'name' => t('Creators'),
        'description' => t('Creators of the feed item.'),
      ),
      'keywords' => array(
        'name' => t('Keywords'),
        'description' => t('Keywords of the feed item.'),
      ),
        ) + parent::getMappingSources();
  }

}