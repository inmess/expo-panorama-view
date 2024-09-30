import { 
    StyleSheet, 
    Text, 
    View, 
    Button, 
    Image,
    Modal,
    ScrollView,
    TouchableOpacity,
    SafeAreaView
} from 'react-native';
import { 
    ExpoPanoramaView, 
    hello 
} from 'expo-panorama-view';
import { useEffect, useState } from 'react';
import * as MediaLibrary from 'expo-media-library';

export default function App() {

    const [ isPlaying, setIsPlaying ] = useState(false);
    const [ url, setUrl ] = useState('');
    const [ albums, setAlbums ] = useState<MediaLibrary.Album[] | null>(null);
    const [ permissionResponse, requestPermission ] = MediaLibrary.usePermissions();
    const [ modalVisible, setModalVisible ] = useState(false);

    const getAlbums = async () => {
        if (!permissionResponse || permissionResponse.status !== 'granted') {
            
            
            await requestPermission();
        }
        console.log("accessPrivileges", permissionResponse?.accessPrivileges);
        const fetchedAlbums = await MediaLibrary.getAlbumsAsync({
            includeSmartAlbums: true,
        });
        console.log("fetchedAlbums: ",fetchedAlbums);
        
        setAlbums(fetchedAlbums);
        setModalVisible(true);
    }

    const onChooseAsset = async (asset: MediaLibrary.Asset) => {
        console.log(asset.uri);
        setModalVisible(false);
        setUrl(asset.uri);
        setIsPlaying(true);
    }


    return (
        <SafeAreaView style={styles.container}>
            <Text>Expo Panorama View {hello()}</Text>
            <Text>{url}</Text>
            <Button title="Get Albums" onPress={getAlbums} />
            <Modal
                animationType="slide"
                transparent={false}
                visible={modalVisible}
                onRequestClose={() => {
                    setModalVisible(false);
                }}
                style={{ flex: 1}}
            >
                <Button title="Close" onPress={() => setModalVisible(false)} />
                <ScrollView contentContainerStyle={{ }}>
                    {albums && albums.map((album, idx) => (
                        <AlbumEntry key={idx} album={album} onChooseAsset={onChooseAsset} />
                    ))}
                </ScrollView>
            </Modal>
            <View style={{height: 300, width: '100%'}}>
                {url ? <ExpoPanoramaView
                    url={url}
                    onPlayStateChanged={(event) => {
                        console.log(event.nativeEvent);
                    }}
                    onProgress={(event) => {
                        console.log(event);
                    }}  
                    isPlaying={isPlaying}
                    
                    style={{ flex: 1 }}
                    onLog={event => console.log("[PLAYER LOG] ", event.nativeEvent)}
                />: <View style={{flex: 1, backgroundColor: 'black'}} />}
                
            </View>
            <Button title={isPlaying ? "pause": "play"} onPress={() => setIsPlaying(p => !p)} />
            
        </SafeAreaView>
    );
}

function AlbumEntry({ 
    album, 
    onChooseAsset 
} : { 
    album: MediaLibrary.Album,
    onChooseAsset?: (asset: MediaLibrary.Asset) => void
}) {
    const [assets, setAssets] = useState<MediaLibrary.Asset[]>([]);
  
    useEffect(() => {
        async function getAlbumAssets() {
            console.log(album);
            
            const albumAssets = await MediaLibrary.getAssetsAsync({ album, mediaType: MediaLibrary.MediaType.video });
            console.log("albumAssets: ", albumAssets);
            setAssets(albumAssets.assets);
        }
        getAlbumAssets();
    }, [album]);
  
    return (
        <View key={album.id} style={styles.albumContainer}>
            <Text>
                {album.title} - {album.assetCount ?? 'no'} assets
            </Text>
            <View style={styles.albumAssetsContainer}>
                {assets && assets.map((asset, idx) => (
                    <TouchableOpacity 
                    key={idx} 
                    style={{ width: '100%', padding: 4 }}
                    onPress={() => onChooseAsset && onChooseAsset(asset)}>
                        <Text style={{margin: 4, fontSize: 20}}>{asset.filename}</Text>
                    </TouchableOpacity>
                ))}
            </View>
        </View>
    );
  }
  

const styles = StyleSheet.create({
    container: {
        flex: 1,
        backgroundColor: '#fff',
        alignItems: 'center',
        justifyContent: 'center',
    },
    albumContainer: {
        paddingHorizontal: 20,
        marginBottom: 12,
        gap: 4,
    },
      albumAssetsContainer: {
        flexDirection: 'row',
        flexWrap: 'wrap',
    },
});
