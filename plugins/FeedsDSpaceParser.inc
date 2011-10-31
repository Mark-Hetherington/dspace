<?php

/**
 * @file
 * Feeds DSpace parser
 */

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

      // Dublin Core Metadata
      $metadata = (string) $item->metadata;
      $metadata = simplexml_load_string("<metadata>" . $metadata . "</metadata>");

      // DC.type
      $type = $metadata->xpath('/metadata/meta[@name = "DC.type"]/@content');
      $items['type'] = (string) $type[0]->content;

      // DC.identifier
      $identifier = $metadata->xpath('/metadata/meta[@name = "DC.identifier"]/@content');
      $items['identifier'] = (string) $identifier[0]->content;

      // DC.number
      $number = $metadata->xpath('/metadata/meta[@name = "DC.relation" and not(@scheme)]/@content');
      $items['number'] = (string) $number[0]->content;

      // DC.creator
      $creators = $metadata->xpath('/metadata/meta[@name = "DC.creator"]/@content');
      foreach ($creators as $creator) {
        $items['creators'][] = (string) $creator;
      }

      // DC.subject
      $keywords = $metadata->xpath('/metadata/meta[@name = "DC.subject"]/@content');
      foreach ($keywords as $keyword) {
        $items['keywords'][] = (string) $keyword;
      }

      // DCTERMS.abstract
      $abstract = $metadata->xpath('/metadata/meta[@name = "DCTERMS.abstract"]/@content');
      $items['abstract'] = (string) $abstract[0]->content;

      // DCTERMS.issued
      $issued = $metadata->xpath('/metadata/meta[@name = "DCTERMS.issued"]/@content');
      $items['issued'] = (string) $issued[0]->content;

      // DCTERMS.bibliographicCitation
      $citation = $metadata->xpath('/metadata/meta[@name = "DCTERMS.bibliographicCitation"]/@content');
      $items['citation'] = (string) $citation[0]->content;

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
      'submitter' => array(
        'name' => t('Submitter'),
        'description' => t('Submitter of the feed item.'),
      ),
      'type' => array(
        'name' => t('Type'),
        'description' => t('Publication type of the feed item.'),
      ),
      'identifier' => array(
        'name' => t('Identifier'),
        'description' => t('Identifier of the feed item.'),
      ),
      'number' => array(
        'name' => t('Number'),
        'description' => t('Number of the feed item.'),
      ),
      'creators' => array(
        'name' => t('Creators'),
        'description' => t('Creators of the feed item.'),
      ),
      'keywords' => array(
        'name' => t('Keywords'),
        'description' => t('Keywords of the feed item.'),
      ),
      'abstract' => array(
        'name' => t('Abstract'),
        'description' => t('Abstract of the feed item.'),
      ),
      'issued' => array(
        'name' => t('Issued'),
        'description' => t('Issue Year of the feed item.'),
      ),
      'citation' => array(
        'name' => t('Citation'),
        'description' => t('Bibliographic citation of the feed item.'),
      )
    );
  }

}