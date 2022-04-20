# cta

<!-- Identifies similar images in the directory using imagehash.
Method: 
  ahash:          Average hash
  phash:          Perceptual hash
  dhash:          Difference hash
  whash-haar:     Haar wavelet hash
  whash-db4:      Daubechies wavelet hash
  colorhash:      HSV color hash
  crop-resistant: Crop-resistant hash -->

# Pour trouver les images similaires dans le dossier d'images
python fsi.py [ahash|phash|dhash|...] [<directory>]