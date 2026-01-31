grep -E '"[45][0-9]{2}' includes/statusCodes.hpp  | sed -E 's/.*"(([0-9]{3}) [^"]*)".*/\2|\1/' | while IFS="|" read -r code msg; do
    echo "<html><body style='font-family:sans-serif; text-align:center; padding-top:20%'><h1>$msg</h1></body></html>" > classes/Location/default_error_pages/"${code}.html" 
    echo "Fichier ${code}.html créé."
done
