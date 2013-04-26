<?php

/**
 * @author James Hartig
 * @copyright 2011
 */

class gsSearch extends gsAPI{

    const MAX_PARALLEL_SEARCHES = 10;

    private $parent;
    private $id = null;
	private $artist = null;
	private $album = null;
	private $title = null;
    private $changed = true;
	private $exact;
	private $results = null;
    private $called = "";

    function gsSearch(&$parent=null){
	   if (!$parent) {
	       $this->parent = gsAPI::getInstance();
       } else {
            $this->parent = $parent;
       }
	}

	public function setArtist($artist){
        $this->changed = true;
		$this->artist = $artist;
	}

	public function setTitle($title){
        $this->changed = true;
		$this->title = $title;
	}

	public function setAlbum($album){
        $this->changed = true;
		$this->album = $album;
	}

    public function setResults($results) {
        $this->results = $results;
        $this->changed = false;
    }

	public function clear(){ //clears all the above search params
		$this->album = null;
		$this->artist = null;
		$this->title = null;
		$this->listing = null;
		$this->results = null;
        $this->changed = true;
	}

    //normalizes search and gets an ID
    public function getUniqueID() {
        if (!$this->id || $this->changed) {
            $query_str = "";
    		if (!empty($this->title)){
    			$query_str .= " s:".$this->title;
    		}
    		if (!empty($this->artist)){
            	$query_str .= " a:".$this->artist;
     		}
    		 if (!empty($this->album)){
            	$query_str .= " l:".$this->album;
      		}
            $query_str =
            preg_replace("/([\!\?\.\,])[\!\?\.\,]+/", "{1}", //remove multiple !?,. characters
                str_replace(array("{", "}", "<", ">", "@", "$", "%", "~", "#", "*", "|", "/", "_", ";", "^"), "",//remove stupid characters
                    preg_replace("/[\s]{2,}/", " ", //replace multiple spaces
                        strtolower( //lowercase
                            trim($query_str) //trim duh
                        )
                    )
                )
            );
            $this->id = md5($query_str);
        }
        return $this->id;
    }

    /*public function singleSongSearch() {
        //todo: this
        if (count($songs['songs'])==1 && $page==1){
            return $songs['songs'][0];
        }

        if (!$this->exact) {
			foreach ($songs['songs'] AS $song){
			     //check for exact match
                if (!empty($this->title) && !empty($this->artist) && !empty($this->album)) {
                    if ((strtolower($this->title) === strtolower($song['SongName']) || ((int)$this->title && (int)$this->title === (int)$song['SongID']))
                        && (strtolower($this->album) === strtolower($song['AlbumName']) || ((int)$this->album && (int)$this->album === (int)$song['AlbumID']))
                        && (strtolower($this->artist) === strtolower($song['ArtistName']) || ((int)$this->artist && (int)$this->artist === (int)$song['ArtistID']))) {
                        $this->exact = $song;
                        break;
                    }
                } elseif (!empty($this->title) && !empty($this->artist)) {
                    if ((strtolower($this->title) === strtolower($song['SongName']) || ((int)$this->title && (int)$this->title === (int)$song['SongID']))
                        && (strtolower($this->artist) === strtolower($song['ArtistName']) || ((int)$this->artist && (int)$this->artist === (int)$song['ArtistID']))) {
                        $this->exact = $song;
                        break;
                    }
                } elseif (!empty($this->title) && !empty($this->album)) {
                    if ((strtolower($this->title) === strtolower($song['SongName']) || ((int)$this->title && (int)$this->title === (int)$song['SongID']))
                        && (strtolower($this->album) === strtolower($song['AlbumName']) || ((int)$this->album && (int)$this->album === (int)$song['AlbumID']))) {
                        $this->exact = $song;
                        break;
                    }
                } elseif (!empty($this->artist) && !empty($this->album)) {
                    if ((strtolower($this->album) === strtolower($song['AlbumName']) || ((int)$this->album && (int)$this->album === (int)$song['AlbumID']))
                        && (strtolower($this->artist) === strtolower($song['ArtistName']) || ((int)$this->artist && (int)$this->artist === (int)$song['ArtistID']))) {
                        $this->exact = $song;
                        break;
                    }
                } elseif (!empty($this->title)) {
                    if (strtolower($this->title) === strtolower($song['SongName']) || ((int)$this->title && (int)$this->title === (int)$song['SongID'])) {
                        $this->exact = $song;
                        break;
                    }
                } elseif (!empty($this->artist)) {
                    if (strtolower($this->artist) === strtolower($song['ArtistName']) || ((int)$this->artist && (int)$this->artist === (int)$song['ArtistID'])) {
                        $this->exact = $song;
                        break;
                    }
                } elseif (!empty($this->album)) {
                    if (strtolower($this->album) === strtolower($song['AlbumName']) || ((int)$this->album && (int)$this->album === (int)$song['AlbumID'])) {
                        $this->exact = $song;
                        break;
                    }
                }
			}
        }
    }*/

	private static function performSearch($method, $query, $country=null, $max=null){
        $results = array();
  		for($page=1;$page<=2;$page++){
  		    switch($method) {
  		        case "getSongSearchResults":
                    $searchResults = parent::getSongSearchResults($query, $country, ($max ? $max : 91), ($page-1)*90);
                    break;
                case "getArtistSearchResults":
                case "getAlbumSearchResults":
                    $searchResults = call_user_func(array(parent::getInstance(), $method), $query, ($max ? $max : 91), ($page-1)*90);
                    break;
                default:
                    return false;
                    break;
  		    }

			if ($searchResults === false || count($searchResults)<1) {
				break;
            }

            if (count($searchResults) > 90 && (!$max || $max > 100)){
                array_pop($searchResults); //we need to check if there are more results
            }

            self::appendResults($searchResults, $results);

			if (count($searchResults) < 90 || ($max && count($results) > $max)) {
				break;
            }
        }
        if ($max) {
            return array_slice($results, 0, $max, true);
        } else {
            return $results;
        }
	}

	public function songSearchResults($max = null)
    {
        //build request

        $query_str = $this->buildQuery("song");

		if (empty($query_str)) {
            return array();
        }

        if ($this->called != __METHOD__) {
            $this->changed = true;
        }

        //we always get at least 50
        if ($this->changed || (count($this->results) >= 50 && $max > count($this->results))) {
            $this->results = null;
            $this->changed = false;

            $this->results = self::performSearch("getSongSearchResults", $query_str, $this->parent->country, max($max, 50));
            if ($this->results == false) {
                return false;
            }
            $this->called = __METHOD__;
            return array_slice($this->results, 0, $max, true);
        } else {
            if ($max) {
                return array_slice($this->results, 0, $max, true);
            } else {
                return $this->results;
            }
        }
	}

	public function artistSearchResults()
    {
        //build request

        $query_str = $this->buildQuery("artist");

		if (empty($query_str)) {
            return array();
        }

        if ($this->called != __METHOD__) {
            $this->changed = true;
        }

        //we always get at least 50
        if ($this->changed || (count($this->results) >= 50 && $max > count($this->results))) {
            $this->results = null;
            $this->changed = false;

            $this->results = self::performSearch("getArtistSearchResults", $query_str, max($max, 50));
            if ($this->results == false) {
                return false;
            }
            $this->called = __METHOD__;
            return array_slice($this->results, 0, $max, true);
        } else {
            if ($max) {
                return array_slice($this->results, 0, $max, true);
            } else {
                return $this->results;
            }
        }
	}

	public function albumSearchResults()
    {
        //build request

        $query_str = $this->buildQuery("album");

		if (empty($query_str)) {
            return array();
        }

        if ($this->called != __METHOD__) {
            $this->changed = true;
        }

        //we always get at least 50
        if ($this->changed || (count($this->results) >= 50 && $max > count($this->results))) {
            $this->results = null;
            $this->changed = false;

            $this->results = self::performSearch("getAlbumSearchResults", $query_str, max($max, 50));
            if ($this->results == false) {
                return false;
            }
            $this->called = __METHOD__;
            return array_slice($this->results, 0, $max, true);
        } else {
            if ($max) {
                return array_slice($this->results, 0, $max, true);
            } else {
                return $this->results;
            }
        }
    }

    private function buildQuery($type) {
        $query_str = "";
    	if (!empty($this->title) && (!empty($this->artist) || !empty($this->album) || $type == "artist" || $type == "album")){
			$query_str .= " song:".$this->title;
            if (!empty($this->artist)){
                $query_str .= " artist:".$this->artist;
            }
    		if (!empty($this->album)){
                $query_str .= " album:".$this->album;
      	  }
		} else if (!empty($this->artist)) {
            if (!empty($this->album)){
                $query_str .= " artist:".$this->artist;
                $query_str .= " album:".$this->album;
            } else {
                $query_str .= ($type == "song" || $type == "album" ? " artist:" : "").$this->artist;
            }
		} else {
            $query_str .= ($this->title ? ($type == "artist" || $type == "album" ? " song:" : "").$this->title :
                            ($this->album ? ($type == "song" || $type == "artist" ? " album:" : "").$this->album : ""));
		}
        $query_str = trim($query_str);
        return $query_str;
    }

	private static function appendResults($results, &$toResults){
	    if (!is_array($toResults)) {
	       $toResults = $results;
		} else {
			$start = count($toResults);
            $i = 0;
			foreach($results AS $v) {
				$toResults[($i++)+$start] = $v;
            }
		}
	}
}

?>