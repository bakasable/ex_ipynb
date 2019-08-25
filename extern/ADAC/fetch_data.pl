use strict;
use WWW::Mechanize ();
my $mech = WWW::Mechanize->new();
use Data::Dumper;


my $url = 'https://www.adac.de/infotestrat/autodatenbank/autokosten/suchergebnis.aspx';
$mech->get( $url );

print Dumper $mech->forms;
