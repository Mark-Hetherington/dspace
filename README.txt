Introduction
------------

DSpace is the software of choice for academic, non-profit, and commercial
organizations building open digital repositories. It is free and easy to install
"out of the box" and completely customizable to fit the needs of any organization.

DSpace preserves and enables easy and open access to all types of digital
content including text, images, moving images, mpegs and data sets. And with an
ever-growing community of developers, committed to continuously expanding and 
improving the software, each DSpace installation benefits from the next.

The goal of this module is to parse a DSpace REST XML feed using the Feeds 
module and process the feed items into nodes.


Installation
------------

After you enable the "dspace" module:

1) go to admin/structure/feeds
2) edit or add an importer
3) under "Parser" choose "DSpace Feeds parser" and click "Save"
4) under "Mappings" choose the DSpace maaping source with the appropriate 
   targets then click "Save"

Once the importer is created, go to /import, click the newly created import.
Under "URL" enter your DSpace REST path to your collection
(e.g. http://dataspace.example.com/rest/collections/123.xml)