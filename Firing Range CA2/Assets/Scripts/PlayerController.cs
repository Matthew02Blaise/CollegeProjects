using System.Collections;
using System.Collections.Generic;
//using UnityEditor.VersionControl;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.UIElements;
using TMPro;

public class PlayerController : MonoBehaviour
{
    //players speed
    public float moveSpeed;

    //drag
    public float groundDrag;

    //jump variables
    public float jumpForce;
    public float jumpCooldown;
    public float airMultiplier;
    bool readyToJump;

    public KeyCode jumpKey = KeyCode.Space;

    public float playerHeight;
    public LayerMask whatIsGround;
    bool grounded;

    //orientation store
    public Transform orient;

    //input variables
    float verticalInput;
    float horizontalInput;

    //movement vector
    Vector3 moveDirection;

    //rigidbody object
    Rigidbody rb;

    //Sound variables
    public float ClipLength = 1f;
    public GameObject JumpClip;

    //Pickup
    public TextMeshProUGUI PickupText;

    //Speed Pickup
    public GameObject speedUp;
    public float speedIncrease;
    public float speedTimer;

    //Jump Pickup
    public GameObject JumpPickUp;
    public float jumpIncrease;
    public float jumpTimer;

    // Start is called before the first frame update
    void Start()
    {
        //initializing rigidbody
        rb = GetComponent<Rigidbody>();
        
        //freeze object
        rb.freezeRotation = true;
        
        //Set cooldown to true to allow for jump
        JumpCooldown();

        JumpClip.SetActive(false);
    }

    // Update is called once per frame
    void Update()
    {
        //using raycast to check if player is on the ground
        grounded = Physics.Raycast(transform.position, Vector3.down, playerHeight * 0.5f + 0.2f, whatIsGround);

        //checking for input every tick
        MyInput();
        
        //controls player speed
        SpeedControl();

        //stopping from movement feeling floaty
        if(grounded)
        {
            rb.drag = groundDrag;
        }
        else
        {
            rb.drag = 0;
        }
    }

    private void FixedUpdate()
    {
        //calls move code every tick
        MovePlayer();
    }

    private void MyInput()
    {
        //Input for movement
        horizontalInput = Input.GetAxis("Horizontal");
        verticalInput = Input.GetAxis("Vertical");

        //Input for jump
        if(Input.GetKey(jumpKey) && readyToJump && grounded)
        {
            //enables jump cooldown
            readyToJump = false;

            //calls jump code
            Jump();
            StartCoroutine(JumpSound());

            //resets cooldown
            Invoke(nameof(JumpCooldown), jumpCooldown);
        }
    }

    private void MovePlayer()
    {
        //move player
        moveDirection = orient.forward * verticalInput + orient.right * horizontalInput;

        //controls force added based on if player is in the air or not
        if (grounded)
        {
            rb.AddForce(moveDirection.normalized * moveSpeed * 1f, ForceMode.Impulse);

        }
        else if(!grounded)
        {
            rb.AddForce(moveDirection.normalized * moveSpeed * 1f * airMultiplier, ForceMode.Impulse);
        }
    }

    private void SpeedControl()
    {
        //vector for flat velocity
        Vector3 flatVelocity = new Vector3(rb.velocity.x, 0, rb.velocity.z);

        //if velocity is greater than moveSpeed variable, bring velocity down to match
        if(flatVelocity.magnitude > moveSpeed)
        {
            Vector3 limitedVelocity = flatVelocity.normalized * moveSpeed;
            rb.velocity = new Vector3(limitedVelocity.x, rb.velocity.y, limitedVelocity.z);
        }
    }

    private void Jump()
    {
        //reset y pos
        rb.velocity = new Vector3(rb.velocity.x, 0f, rb.velocity.z);

        //add force to player to jump
        rb.AddForce(transform.up * jumpForce, ForceMode.Impulse);
    }

    private void JumpCooldown()
    {
        //allowing for jump
        readyToJump = true;
    }

    IEnumerator JumpSound()
    {
        JumpClip.SetActive(true);
        yield return new WaitForSeconds(ClipLength);
        JumpClip.SetActive(false);
    }

    private void speedPickup()
    {

    }
    private void OnTriggerEnter(Collider other)
    {
        if (other.gameObject == speedUp)
        {
            StartCoroutine(SpeedBoost());
            Destroy(speedUp);
            StartCoroutine(TextForPickup("Speed boost activated for 10 seconds!"));
        }

        if (other.gameObject == JumpPickUp)
        {
            StartCoroutine(JumpBoost());
            Destroy(JumpPickUp);
            StartCoroutine(TextForPickup("Double Jump Activated for 10 seconds!"));
        }
    }

    IEnumerator SpeedBoost()
    {
        moveSpeed *= speedIncrease;
        yield return new WaitForSeconds(speedTimer);
        moveSpeed /= speedIncrease;
    }

    IEnumerator JumpBoost()
    {
        jumpForce *= jumpIncrease; 
        yield return new WaitForSeconds(jumpTimer);
        jumpForce /= jumpIncrease;
    }

    IEnumerator TextForPickup(string message)
    {
        PickupText.text = message;
        PickupText.gameObject.SetActive(true);
        yield return new WaitForSeconds(3);
        PickupText.gameObject.SetActive(false);
    }
}
